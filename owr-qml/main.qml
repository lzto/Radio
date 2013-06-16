import QtQuick 1.1

Item
{
	width: 640
	height: 280
	Item
	{
		id:item_hz
		width:parent.width
		height:parent.height*0.618
		Rectangle
		{
			anchors.fill:parent
			color:"black"
			border.color: "black"
			border.width: 5
 			radius: 0
		}

		Text
		{
			id:label_hz
			text:"88.7 MHz"
			color:"yellow"
			font.pixelSize : 64
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			anchors.fill:parent
		}
	}
	Item
	{
		id:btn_pre
		width:parent.width/2
		anchors
		{
			top:item_hz.bottom
			bottom:parent.bottom
			left:parent.left
			right:btn_next.left
		}
		Rectangle
		{
			anchors.fill:parent
			color:"lightblue"
			border.color: "black"
			border.width: 5
			radius: 0
		}
		Text
		{
			text:"\<"
			font.pixelSize : 30
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			anchors.fill:parent
		}
		MouseArea
		{
			anchors.fill:parent
			onClicked:
			{
				owr.slot_pre();
				//console.log("pre");
			}
		}
	}
	Item
	{
		id:btn_next
		width:parent.width/2
		anchors
		{
			top:item_hz.bottom
			bottom:parent.bottom
			left:btn_pre.right
			right:parent.right
		}
		Rectangle
		{
			anchors.fill:parent
			color:"lightblue"
			border.color: "black"
			border.width: 5
 			radius: 0
		}
		Text
		{
			text:"\>"
			font.pixelSize : 30
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			anchors.fill:parent
		}
		MouseArea
		{
			anchors.fill:parent
			onClicked:
			{
				owr.slot_next();
				//console.log("next");
			}
		}
	}
	function updateFreq(text)
	{
		label_hz.text = text
	}

}


