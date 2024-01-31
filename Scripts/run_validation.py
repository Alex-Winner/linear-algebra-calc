import subprocess
import os
import time

# Paths
script_dir = os.path.dirname(os.path.realpath(__file__))
parent_dir = os.path.dirname(script_dir)
input_dir = os.path.join(parent_dir, "validation/input")
output_dir = os.path.join(parent_dir, "validation/output")

executable = "mainmat"

# Ensure output directory exists
os.makedirs(output_dir, exist_ok=True)

# Run 'make' in the parent directory
subprocess.run("make", shell=True, cwd=parent_dir)

# Run 'make clean' in the parent directory
subprocess.run("make clean", shell=True, cwd=parent_dir)

# Getting the list of test files
test_files = [f for f in os.listdir(input_dir) if f.endswith(".txt")]

total_files = len(test_files)
processed_files = 0
bar_length = 50  # Length of the progress bar in characters

start_time = time.time()
for test_file in test_files:

    test_file_path = os.path.join(input_dir, test_file)

    # Modify the output file name by adding '_output' tag before the extension
    base_name, ext = os.path.splitext(test_file)
    output_file_name = f"{base_name}_output{ext}"
    output_file_path = os.path.join(output_dir, output_file_name)

    # Extract relative paths from the parent directory for display
    relative_test_file_path = os.path.relpath(test_file_path, parent_dir)
    relative_output_file_path = os.path.relpath(output_file_path, parent_dir)

    # Run the program with the test file as input, redirect output to a file
    run_command = f"../{executable} < {test_file_path} > {output_file_path}"
    process = subprocess.run(run_command, shell=True, capture_output=True, text=True, cwd=script_dir)

    # Check for errors during execution
    if process.stderr:
        print("Errors:")
        print(process.stderr)

    

    # Update and print the progress
    processed_files += 1
    progress_percentage = (processed_files / total_files) * 100
    progress_bar_filled = int(bar_length * processed_files / total_files)
    progress_bar = "##" * progress_bar_filled
    progress_bar += "  " * (bar_length - progress_bar_filled)
    print(f"Progress: [{processed_files}/{total_files}] \t[{progress_bar}] {progress_percentage:.2f}%", end = '\r')      

# After processing all files
end_time = time.time()
print(f"\nAll files processed in {end_time-start_time:.4f} seconds")