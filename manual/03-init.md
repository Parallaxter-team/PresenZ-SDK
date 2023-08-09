# Initialization/Termination {#initTermination}

# 3.1 Setting up PresenZ error reporting system

You can set up and redirect the PresenZ error reporting system to forward all information, warnings, and errors of PresenZ to your own logging mechanism. This can be achieved with a small set of methods defined in PzAppLogger.h.

For example:

    using  namespace PresenZ::Logger;
    
      
    PzSetDateHeader(false); // disable time stamp in front of messages  
    PzSetLogLevelHeader(false); // disable [WARNING]/[ERROR] tags  
    PzSetConsole(false); // disable stdout printfPzSetCallBackLogLevel(LL_Trace, loggerCallback, static_cast<void *>(this)); PzSetCallbackCarriageReturnMode(CR_NoCarriageReturn);
    
    Where the loggerCallback can follow this implementation:
    
    void loggerCallback(const LogLevel &lvl, const  char* message, void *userData)  
    {  
		MyLogger *logger = static_cast<MyLogger *>(userData);  
		switch (lvl) {
		case LL_Info: logger->info(message); break;  
		case LL_Warning: logger->warning(message); break;  
		case LL_Error: logger->error(message); break;  
		case LL_Debug:case LL_Trace: logger->trace(message); break;  
		};  
    }
	
# 3.2 Phase initialization

Before actually doing the rendering, you need to specify to PresenZ the type of phase that you are about to render

	PzInitPhase(Detect, PRESENZ_DEVELOP);

Or

	PzInitPhase(Render, PRESENZ_DEVELOP);

The first parameter is the phase type (detect or render) and the second parameter is which engine is used to make the render. You can use PRESENZ_DEVELOP during development time.

# 3.3 Phase set up

After initializing a phase, it is necessary to configure the phase with the correct parameters for your render. A series of setter functions are provided to do this. 

Here is the bare minimal setter functions to call for the detection phase :

    PresenZ::Logger::PzSetConsole(true);
    PresenZ::Phase::PzInitPhase(PresenZ::Phase::Detect, PresenZ::Util::RenderingEngineId::PRESENZ_DEVELOP);
    PresenZ::Phase::PzSetOutFilePath("render.przDetect");
    PresenZ::Phase::PzSetDraft(false);
    PresenZ::Phase::PzSetZovOffset(0, 0, 0);
    PresenZ::Phase::PzSetCurrentFrame(0);
    PresenZ::Phase::PzSetOutputResolution(3000, 2000);
    PresenZ::Phase::PzSetRenderTransparencyMode(PresenZ::Phase::TransparencyRenderingType::PRZ_REGULAR);
    const PresenZ::Phase::PzResolutionParam blockCountAndResolution = PresenZ::Phase::PzComputeRenderingResolutionParameters(3000, 2000);
    PresenZ::Phase::PzSetRenderingResolutionParameters(blockCountAndResolution;
    PresenZ::Phase::PzSetBucketSize(64, 64);
    PresenZ::Phase::PzPhaseBegin();

You probably want to add others setters to make the rendering meaningful, like the camera matrix :

	PresenZ::Phase::PzSetCameraToWorldMatrix(getNozM4Identity());
	
A thorough list of initializers can be found in PzPhaseAPI.h.
	
	
## 3.3.1 Setting up AOVs

AOVS are arbitrary values that can be set per sample rendered. During initialization, you can declare their name and type. AOVs can also be identified by an alias, which is an integer value between 0 and 65535. These AOVs are given as examples and do not reflect any implementation:

	PzRenderPhaseRegisterAov(0, "computationTime", AOVType::FLOAT);  
	PzRenderPhaseRegisterAov(1, "diffuse_color", AOVType::RGB);  
	PzRenderPhaseRegisterAov(2, "bounces", AOVType::INT);

You can register the following types as AOVs: integer, floating point, boolean, color, 2d vector, 3d vector, and 4d vector.

PresenZ has a set of custom AOVs that are activated depending on the parameters set in chapter 3.3.

## 3.3.2 Setting up Rendering Resolution

### 3.3.2.1 First phase

The first phase resolution must be the same as the desired prz image resolution. There are a few requirements :

-   image ratio has to be 3:2, so if X=3000, then Y=2000
-   resolution has to be a multiple of 8, 1800x1200 is correct but 750x500 is not
-   horizontal resolution must be between 312 and 6000

The resolution can be set with:

	PzSetOutputResolution(3000, 2000);

### 3.3.2.2 Second phase

For the second phase, PresenZ is a bit more flexible, there are two possibilities :

-   User picks the resolution (recommended)

In the second phase, the user may pick what would be the render target resolution. Care needs to be taken, it is possible that there are more points to be shaded than what the render target resolution can contain. The plugin must then kick-start multiple renders one after the other so it can cover all of the points.

	const PzResolutionParam rp = PzComputeRenderingResolutionParameters(3000, 2000);  
  
	// rp contains the number of renders to be performed  
	PzSetRenderingResolutionParameters(rp);

This solution is especially recommended if the quality of your rendering is dependent on the resolution of the render target (ie. resolution-dependent features like subdivisions/displacement) If this is the case, use the optimal render resolution for your project and ask PresenZ how many blocks need to be processed.

-   Let PresenZ picks the resolution

If the render target resolution has no impact on the quality of your renders, you can ask PresenZ what would be the ideal resolution that will ensure that every point in the final image is shaded.

	const PzResolutionParam rp = PzGetRenderingResolutionParameters() ; // rp will contain the ideal resolution for the render phase  
	myRenderer->setRenderTargetRes(rp.resolutionX, rp.resolutionY);  
	PzSetRenderingResolutionParameters(rp);

# 3.4 Phase Begin and Termination

After setting all the necessary parameters, it is time to execute the desired phase. This is achieved by calling PzPhaseBegin(), which will execute the phase previously initialized with PzInitPhase():

	PzPhaseBegin();

Finally, when the rendering is finished, PzPhaseTerminate() needs to be invoked. This function will write all the rendering data to the corresponding file. Usually the “option” parameter is set to “WRITE_TO_DISK”, however it can also be set to “SKIP_DISK_IO” which will not write the buckets to a file. This option can be useful when doing distributed rendering as the data is already stored elsewhere on the network.

	PzPhaseTerminate(WRITE_TO_DISK);	