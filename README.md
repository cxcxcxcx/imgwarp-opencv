# imgwarp-opencv
Warps an image by a few control points. For C++ and OpenCV 2.0+. 

Currently includes Moving Least Square warping (for sparse control points, see reference), and piece-wise affine warping (for dense control points only).

A JavaScript version is [here](http://chenxing.name/fun/imgwarp-js/).

| ![](https://raw.githubusercontent.com/cxcxcxcx/imgwarp-opencv/master/data/imgs/tux.jpg) | ![](https://github.com/cxcxcxcx/imgwarp-opencv/blob/wiki/imgs/tux_sim.png?raw=true) |
|:--------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------|
| Linux Tux | Warped Tux |

| ![](https://github.com/cxcxcxcx/imgwarp-opencv/blob/wiki/imgs/monalisa_ori.jpg) | ![](https://github.com/cxcxcxcx/imgwarp-opencv/blob/wiki/imgs/monalisa_warped.png) |
|:--------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------|
| Image from Schaefer's paper | Warped as Schaefer did |

The demo application:

![](https://github.com/cxcxcxcx/imgwarp-opencv/blob/wiki/imgs/ui.png)

Papers implemented:
Image Deformation Using Moving Least Squares
Schaefer S., McPhail T. and Warren J.
ACM SIGGRAPH 2006, pages 533-540


Automatically exported from code.google.com/p/imgwarp-opencv
(Deprecated) This is used in [an interactive face deforming project](http://code.google.com/p/faceworkshop/).
