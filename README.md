# quantstuff

A C++ engine for live market data, predictive modeling, and systematic market conclusions.

## What I’m building
- Fetch market data from APIs
- Parse it into structured objects
- Store and process it in a clean pipeline
- Eventually add analysis modules for indicators and signal detection
- Scale it into a more serious market analysis tool over time

## Current state
- C++ + CMake
- HTTP client for fetching data
- Queue + parser pipeline
- Typed market data structures
- Analyzer interface and momentum analyzer scaffold

## Planned next steps
- Better parsing and validation
- Historical data storage
- Real-time analysis
- Backtesting and indicator modules
- Cleaner architecture and deployment setup

## Why this project
This is mainly a learning project, but the goal is to build something that could grow into a real market analysis tool. It helps me practice:
- C++ design
- data pipelines
- system architecture
- market data processing
- quantitative analysis ideas

## Quick start
```bash
git clone https://github.com/KaliKiu/quantstuff.git
cd quantstuff
mkdir build && cd build
cmake ..
cmake --build .
./meow
