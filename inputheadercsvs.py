import os
import csv
dir_path= "D:/Descargas/ECGDataDenoised"
file_list = os.listdir(dir_path)
lead_names = ['I', 'II', 'III', 'aVR', 'aVL', 'aVF', 'V1', 'V2', 'V3', 'V4', 'V5', 'V6']
for file_name in file_list:
    # Load the file
    with open(os.path.join(dir_path, file_name), mode="r", newline="") as file:
        print(os.path.join(dir_path, file_name))
        # Create a CSV reader object
        reader = csv.reader(file)
        # Read the existing data from the CSV file
        data = [row for row in reader]
        print (data)
    with open(os.path.join(dir_path, file_name), mode="w", newline="") as file:
    # Create a CSV writer object
        writer = csv.writer(file)
    # Write the header row to the CSV file
        writer.writerow(lead_names)
    # Write the existing data back to the CSV file
        writer.writerows(data)
