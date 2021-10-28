#!/bin/bash

TAG="$TRAVIS_BRANCH"
if [ "$TAG" = "master" ]; then
   TAG="latest"
fi

echo "$DOCKER_PASSWORD" | docker login -u $DOCKER_USERNAME --password-stdin

docker build . -t koinos/koinos-cdt:$TAG
