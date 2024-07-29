#!/bin/bash

# Set the log file path
LOG_FILE="system_performance.log"

# Function to get CPU usage
get_cpu_usage() {
    cpu_usage=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}')
    echo "$cpu_usage"
}

# Function to get memory usage
get_memory_usage() {
    # Get the total and used memory from /proc/meminfo
    total_mem=$(grep MemTotal /proc/meminfo | awk '{print $2}')
    used_mem=$(grep MemFree /proc/meminfo | awk '{print $2}')

    # Calculate memory usage
    mem_usage=$((100 - (used_mem * 100 / total_mem)))

    echo "$mem_usage"
}

# Main loop
while true; do
    # Get CPU and memory usage
    cpu_usage=$(get_cpu_usage)
    mem_usage=$(get_memory_usage)

    # Log the data to the file
    echo "$(date +"%Y-%m-%d %H:%M:%S") CPU: $cpu_usage%, Memory: $mem_usage%" >> "$LOG_FILE"

    # Sleep for 2 seconds
    sleep 2
done