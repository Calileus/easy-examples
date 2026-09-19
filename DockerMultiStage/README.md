# DockerMultiStage

This example separates compilation from runtime. The `builder` stage uses GCC, while the final image contains only the compiled executable and a small Debian runtime.

From this directory:

```bash
docker build -t easyexamples-docker-multistage .
docker run --rm easyexamples-docker-multistage
```

Expected output:

```text
Hello from a multi-stage Dockerized C++ example.
```

Compare the image layers with `docker image ls` after building both Docker examples. The important idea is that compiler tools do not need to be copied into the runtime stage.