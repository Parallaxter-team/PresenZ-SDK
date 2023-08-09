# Renderer requirements & recommendations {#requirements}

# 2.1 Requirements


In order for PresenZ to operate correctly with a Renderer, we can define six conditions that need to be met:


## 2.1.1 Control the sub-sampling mechanism


This is only required for the first phase. The first phase must issue exactly 256 samples per pixel. This is not needed in the second phase as it can have its own custom sub-sampling strategy.


## 2.1.2 Ability to start a few renders in a row


This requirement is only necessary for the render phase. The second phase might need to shade more points than the render target resolution may allow. This is resolved by executing multiple render phases one after the other.


## 2.1.3 Ability to check if there’s a line of sight from point A to point B


During the first phase, PresenZ will query the renderer to find out whether a geometry - that it assumes to be obstructed - can be seen from several viewpoints. PresenZ will require a small implementation (callback) that can tell if a point B can be seen from point A.


What we want to know is if there is an actual line of sight: it should ignore glasses and transparent geometry along the way as these do not block the view between the two points.


## 2.1.4 Ability to redefine ray origin/direction (and optionally derivatives)


As PresenZ works with an atypical camera projection/deformation, it can not use a standard orthogonal or 360 camera to achieve its own renders. For this reason, plugins will have to override the ray origin/direction for each sample that is issued.


## 2.1.5 Extract hit location and normal for each sample hit


Every time a sample ray hits an object, PresenZ will need to extract the exact location and the geometric normal for the hit.





## 2.1.6 Shade a target viewed location from a custom viewpoint


The shading operation will need to be performed from a very specific view point instead of the ray origin. For instance, it is usually more desirable to render from the view point of the left or right eye.


# 2.2 Recommandations


The following points are not essential but can greatly facilitate the implementation of a PresenZ plugin for your renderer.


## 2.2.1 Processing patch of images in independent threads


Presenz is built around the concept that multiple threads will independently render parts of your render target. While not mandatory, it is an advantage for seamless integration of the plugin SDK (see point 5 buckets and threading).


## 2.2.2 Ability to extract user properties from geometries


In order to speed up identification of hair, light and transparent geometry, it would be very convenient if objects in the scene could have user properties. Ideally, they should be defined at authoring time in order to make sure that the right geometry is interpreted correctly by PresenZ.


## 2.2.3 Ability to shade twice in a row from different viewpoint


Specifically for stereoscopic images, you might need colors that are different for the left and the right eye. This will need to be computed during the render phase. For this reason, it is convenient to be able to change the rendering properties on the fly and request a sample color as if it was seen from the right eye and then from the left eye.


## 2.2.4 Ability to extract velocity at specific location


Specifically for animation: VR headsets might be working at refresh rates that are different from common display devices. So, if possible, PresenZ can save the velocity of specific world locations so that it can later be used to interpolate correctly between two frames giving smoother animation.