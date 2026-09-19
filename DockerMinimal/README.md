# DockerMinimal

The smallest Docker example in Easy C++ Examples. It copies one C++ source file into a compiler image, builds it, and runs the result.

From this directory:

```bash
docker build -t easyexamples-docker-minimal .
docker run --rm easyexamples-docker-minimal
```

Expected output:

```text
Hello from a minimal Dockerized C++ example.
```

This example introduces `Dockerfile`, `docker build`, `docker run`, `WORKDIR`, `COPY`, and `CMD`.