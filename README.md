# Simple-Painter
Simple Paint Program, with Copy/Paste/Clear made with QT and C++.

A simple mouse drawing program with a right click context menu that allows you to copy, paste and clear your drawings. I'm using the QImage structure in order to keep track of the pixels that need to be painted on to the canvas.

The way the mouse draw occurs is that each mouse move triggers a move event and so we draw a straight line from the last known position to the current position. In that way it appears we are making a fluid drawing, but it actually consists of linear pixel-length lines.

The copy, paste and clear functionality is all provided by overriding the right-click context menu of the main window class. To perform a copy, we take the current image on the canvas and load it into a mime structure and then into the clipboard. To perform a paste, we load the image from the clipboard and to perform a clear, we fill the image with white (same colour as our background) and then issue a repaint event for the window.

https://user-images.githubusercontent.com/111576658/201375061-169e8d8c-7c76-434f-be6f-fd48bb21d5c1.mp4

