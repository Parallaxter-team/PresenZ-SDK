# Transparency {#transparencies}

# 6.1 Initialization

In regular (default) mode, PresenZ does not expect any transparent geometry in the scene.


    PzSetRenderTransparencyMode(TransparencyRenderingType::PRZ_REGULAR);


If your renderer can handle opaque and transparent geometry at the same time, then you can use :


    PzSetRenderTransparencyMode(TransparencyRenderingType::PRZ_BOTH);


PRZ_BOTH means both transparent and opaque geometry might be detected and shaded during the same render.


If it is impossible to easily differentiate both at render time, then you can enforce an opaque render of the opaque scene followed by a transparent render of the transparent scene with the following calls:


	PzInitPhase(...);
	PzSetRenderTransparencyMode(TransparencyRenderingType::PRZ_OPAQUE);
	PzBeginPhase();
	// do a render of the opaque scene here
	// ...
	PzTerminatePhase();

	/////////////////////////////////////////////////////////////////////////

	PzInitPhase(...);
	PzSetRenderTransparencyMode(TransparencyRenderingType::PRZ_TRANSPARENT);
	PzBeginPhase();
	// do a render of the transparent scene here
	// ...
	PzTerminatePhase();


# 6.2 Easy detection of transparent geometry with tags


In popular authoring tools such as 3D Studio or Maya, it is possible to attach user properties to objects. This can be an easy way to quickly identify if an object is transparent without invoking complex shader evaluation.


# 6.3 Referencing transparent geometry


During the first phase, every detect hit that is part of transparent geometry should be recorded with the field PzDetectSample::isTransparent as true


	PzDetectSample detectSample;    
	// Set sample properties
	// ...

	detectSample.isTransparent = true;
	PzProcessDetectSample(intf, detectSample, bucketId);


Similarly, during the second phase PzAddGlassSampleAov() should be invoked :


	PzRenderSample renderSample;
	// Set sample properties
	// ...

	PzAddGlassSampleAov(renderSample, 1);


The alpha channel of the color component should receive the opacity of the material that is being shaded.


After referencing transparent geometry, the ray should not be stopped and continue its way and keep on notifying hits until it reaches an opaque geometry. At this point, the ray can be stopped and no more work is necessary in this direction.

