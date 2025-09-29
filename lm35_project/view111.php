<?php
// 🕒 Set the local timezone to Cairo (Egypt)
date_default_timezone_set("Africa/Cairo");

// Display the page title centered
echo "<h1 style='text-align:center;'>Temperature Readings with Images</h1>";

// Automatically refresh the page every 5 seconds to show new data
echo "<meta http-equiv='refresh' content='5'>";

// Check if the data file exists
if(file_exists("data.txt")){

    // Read all lines from the file and reverse them to show the latest readings first
    $lines = file("data.txt");

    // Start an HTML table to display the readings
    echo "<table border='1' cellspacing='0' cellpadding='8' style='width:80%; margin:20px auto;
            font-family:Arial; border-collapse:collapse; text-align:center;'>";

    // Table header row with column titles
    echo "<tr style='background:#333; color:#fff;'>
            <th>Time</th>
            <th>Temperature</th>
            <th>Image</th>
          </tr>";

    // Loop through each line in reverse order (latest first)
    foreach(array_reverse($lines) as $line){
        // Initialize variables for time, temperature, and image
        $time = "";
        $temp = "";
        $imgFile = "";

        // Match the line format using regular expression
        // Example line: 2025-09-14 08:23:43 PM - Temp: 34.0 C - IMG: warm.png
        if(preg_match("/^(.?) - Temp: (.?) C - IMG: (.*)$/", trim($line), $matches)){
            $time = $matches[1];       // Extract timestamp
            $temp = $matches[2];       // Extract temperature value
            $imgFile = $matches[3];    // Extract image filename
        }

        // Display the extracted data in a table row
        echo "<tr>
                <td>$time</td>
                <td>$temp °C</td>
                <td><img src='$imgFile' alt='Temp Image' width='120'></td>
              </tr>";
    }

    // Close the table
    echo "</table>";

} else {
    // If the data file doesn't exist, show a warning message
    echo "<p style='color:red; font-weight:bold; text-align:center;'>No data yet.</p>";
}
?>