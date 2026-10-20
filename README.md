# QuantEngine

A C++ engine for live market data, predictive modeling, and systematic market conclusions.

## What I’m building
- Fetch market data from APIs
- Parse it into structured objects
- Store and process it in a clean pipeline
- Analysis modules for indicators and signal detection
- Scale into adding more components / dataflow possibilities

## Dataflow framework
- Built around 3 pillars which lets each above mentioned component be used in different order to form DAG
- Source, Transform and Sink
- Generic programmed, with boundaries set on specific components.

## Current state
- HTTP client for fetching data
- Queue for stream pipeline
- Json Parser
- Typed market data structures
- Analyzer interface and momentum analyzer scaffold
- Framework built, lets components be connected and used.

## Planned next steps
- Implementing Adapters between components so Dataflow framework can used.
- Asynch DAG execution for specific components to enhance speed

## Why this project
This is mainly a learning project, but the goal is to build something that could grow into a real market analysis tool. It helps me practice:
- C++ design
- data pipelines
- system architecture
- market data processing
- quantitative analysis ideas
- api design
- workflow design

## Quick start
Make sure to include an nlohmann/json header file
```bash
git clone https://github.com/KaliKiu/quantstuff.git
cd quantstuff
mkdir build && cd build
cmake ..
cmake --build .
./meow
