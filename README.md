# gpu-mini-projects
## Using the container
* `bash build_container.sh` to build the container from ubuntu 18.04 image.
* `bash podman_enter.sh` to launch bash prompt in the container
  * The container needs unconfined access to access the GPU. The security opts allow this w/o disabling SELinux everywhere.
* The launch directory is mounted to /host and will be read-only.
* Cleanup stuff after continuous rebuilds: `podman system prune`
