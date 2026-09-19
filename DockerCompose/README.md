# DockerCompose

This example uses Docker Compose to build and run one configured C++ service. The environment variable is supplied by `compose.yaml`, so the same image can be run with different greetings without changing the source.

From this directory:

```bash
docker compose up --build --remove-orphans
docker compose down
```

Expected output includes:

```text
Hello from a Docker Compose service.
```

This example introduces a Compose service, a build context, and environment configuration.