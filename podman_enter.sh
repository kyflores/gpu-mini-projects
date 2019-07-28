podman run -it --rm \
	-v $(pwd):/host \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-e DISPLAY=$DISPLAY \
	--security-opt label=disable \
	--security-opt seccomp=unconfined \
	--device=/dev/kfd \
	--device=/dev/dri \
	--group-add video rocm-container:latest
