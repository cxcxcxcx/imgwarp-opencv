For C++ and OpenCV 2.0+. Warp an image by a few control points.

Currently includes Moving Least Square warping (for sparse control points, see reference), and piece-wise affine warping (for dense control points only).

This is used in [an interactive face deforming project](http://code.google.com/p/faceworkshop/).

A JavaScript version is [here](http://chenxing.name/fun/imgwarp-js/).

| ![http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/tux.jpg](http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/tux.jpg) | ![http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/tux_sim.png](http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/tux_sim.png) |
|:--------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------|
| Linux Tux | Warped Tux |

| ![http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/monalisa_ori.jpg](http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/monalisa_ori.jpg) | ![http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/monalisa_warped.png](http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/monalisa_warped.png) |
|:--------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------|
| Image from Schaefer's paper | Warped as Schaefer did |

The demo application:

![http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/ui.png](http://imgwarp-opencv.googlecode.com/svn/wiki/imgs/ui.png)

Papers implemented:
Image Deformation Using Moving Least Squares
Schaefer S., McPhail T. and Warren J.
ACM SIGGRAPH 2006, pages 533-540