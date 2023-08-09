# Misc.: Hair and Animation {#hair}

# 8.1 Hair


A common way to implement hair in 3D authoring software is to have them represented as a (numerous) set of curves or very thin cylinders.


If this is the case, hair might be better considered as strings of particles instead of a typical 2D surface. PresenZ can take advantage of this knowledge and process hair internally in a more accurate way.


If your engine can easily detect that it has hit hair geometry, for example with tags, you can set the “isHair” field to true in PzDetectSample.


	PzDetectSample sample;    
	// ...
	sample.isHair = true;


As hair is considered to be particles, it is allowed to have null sized normals. Hair should only be detected during the Detect Phase. 
This information about the geometry will be conveyed from the Detect Phase to the Render Phase and PresenZ will output the final geometry accordingly.


# 8.2 Animations


## 8.2.1 Frame numbering


Animation can be done by rendering frames one by one. The frame number will be saved before the extension in the output file name. 
Both presenz_merger.exe and presenz_player.exe will detect all the frames in the target directory and will load them in order.


For each render, you will need to invoke PzSetCurrentFrame() with the desired frame number.


    PzSetCurrentFrame(frameNumber);


## 8.2.2 Movement interpolation


As a VR headset may work at a different framerate (i.e.: Oculus VR runs at 90 frame per second), frames might need to be interpolated in order to display smooth movement.


If your renderer support it, you can enable “motion vectors” with


    PzSetMotionVector(true);


During phase set-up. This is only relevant for the rendering phase.


Later, when samples are recorded, you can set the world space velocity for each sample :


    PzRenderSample winSample;
	// ....

	PzAddVelocitySampleAov(winSample, getVelocity(hitPoint));

