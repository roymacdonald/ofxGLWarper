# OFXGLWARPER
## openGL based image warper add-on
Based on the openGL image warper example by Theo Watson.

### Features
* Quad-Warp anything that's being drawn in OF.
* begin() and end() methods to define the warpped elements.
* Easy quad manipulation by draging the quad corners with the mouse and arrow keys for fine control.
* Get screen-to-warpped-coordinates and warpped-to-screen-coordinates methods.
* Setup now requires the resolution of the screen to be passed making it much more flexible.
* Events triggered when warping changes, allowing complex interactions.

### Contributors (many thanks!)
* [Paulo Barcelos](https://github.com/paulobarcelos)
* [Eloi Maduell](https://github.com/eloimaduell)
* [Cyril Communal](https://github.com/CyrCom)

###### Thanks to Arturo and hv_francesco for their suggestions.

### Updates
OpenCV is no longer needed. Switched to use ofxHomography, which is included in this addon.
