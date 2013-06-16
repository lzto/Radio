/* Name: set-freq.c
 * Author: lovewilliam
 * Creation Date: 2011-05-29
 * Tabsize: 4
 * Copyright: (c) 2011 lovewilliam<lovewilliam@gmail.com>
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usb.h>        /* this is libusb */
#include "opendevice.h" /* common code moved to separate module */

#include "../firmware/requests.h"   /* custom request numbers */
#include "../firmware/usbconfig.h"  /* device's VID/PID and names */

static void usage(char *name)
{
	fprintf(stderr, "usage:\n");
	fprintf(stderr, "  %s up ....... turn freq up\n", name);
	fprintf(stderr, "  %s down ...... turn freq down\n", name);
	fprintf(stderr, "  %s set ... set freq of radio\n", name);
	fprintf(stderr, "  %s status ... ask current status of radio\n", name);
	fprintf(stderr, "  %s prog Channel1 Channel2 ... prog channels\n", name);
}

int main(int argc, char **argv)
{
	usb_dev_handle      *handle = NULL;
	const unsigned char rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
	char                vendor[] = {USB_CFG_VENDOR_NAME, 0}, product[] = {USB_CFG_DEVICE_NAME, 0};
	char                buffer[256];
	int                 cnt, vid, pid, isOn;

	usb_init();
	if(argc < 2){   /* we need at least one argument */
		usage(argv[0]);
		exit(1);
	}
	/* compute VID/PID from usbconfig.h so that there is a central source of information */
	vid = rawVid[1] * 256 + rawVid[0];
	pid = rawPid[1] * 256 + rawPid[0];
	/* The following function is in opendevice.c: */
	if(usbOpenDevice(&handle, vid, vendor, pid, product, NULL, NULL, NULL) != 0){
		fprintf(stderr, "Could not find USB device \"%s\" with vid=0x%x pid=0x%x\n", product, vid, pid);
		exit(1);
	}

	if(strcasecmp(argv[1], "status") == 0){
		cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN,
				      CUSTOM_RQ_GET_STATUS, 0, 0, buffer, 5*sizeof(char) , 5000);
		if(cnt < 1){
			if(cnt < 0){
				fprintf(stderr, "USB error: %s\n", usb_strerror());
			}else{
				fprintf(stderr, "only %d bytes received.\n", cnt);
			}
		}else{
			printf("Radio is %s\n", buffer[0] ? "on" : "off");
		}
		unsigned int value;
		memcpy(&value,buffer,4);
		printf("Frequency : %d\n",value);
		unsigned char rx_power = buffer[4];
		printf("RX_POWER : %d\n",rx_power);
	}else if((isOn = (strcasecmp(argv[1], "up") == 0)) || strcasecmp(argv[1], "down") == 0){
		cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
				      CUSTOM_RQ_SET_STATUS, isOn, 0, buffer, 0, 5000);
		if(cnt < 0)
		{
			fprintf(stderr, "USB error: %s\n", usb_strerror());
		}
	}else if(strcasecmp(argv[1], "set") == 0)
	{
		if(argc<3)
		{
			printf("Freq Required.\n");
			exit(0);
		}
		cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
				      CUSTOM_RQ_SET_FREQ,0, 0, buffer, 0, 5000);
		if(cnt < 0)
		{
			fprintf(stderr, "USB error: %s\n", usb_strerror());
		}
		long int freq = atoi(argv[2]);
		memcpy(buffer,&freq,4);
		//write buffer to device;
		printf("Setting Freq %ld\n",freq);
		cnt = usb_control_msg(handle, USB_TYPE_CLASS | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
				      CUSTOM_RQ_SET_FREQ,0, 0, buffer, 4, 5000);
		if(cnt < 0)
		{
			fprintf(stderr, "USB error: %s\n", usb_strerror());
		}
		printf("Done!\n");
	}else if(strcasecmp(argv[1], "prog") == 0)
	{
		int i = 0;
		int pos = 1;
		int channels = 0;
		memset(buffer, 0, sizeof(buffer));
		
		buffer[0] = (char)(argc - 2);
		channels = buffer[0];

		for(i = 2;i<channels+2;i++)
		{
			int temp = atoi(argv[i]);
			char tc[4];
			memcpy(tc,&temp,4);
			memcpy(buffer+pos,tc,4);
			pos+=4;
		}

		printf("programming %d channels with %d bytes\n",channels,pos);
		cnt = usb_control_msg(handle, USB_TYPE_CLASS | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
				      CUSTOM_RQ_PROG_CHANNELS,0, 0, buffer,pos, 5000);
		if(cnt<0)
		{
			fprintf(stderr,"Error prog channels! Err:%s\n",usb_strerror());
		}
	}else
	{
		usage(argv[0]);
		exit(1);
	}
	usb_close(handle);
	return 0;
}
