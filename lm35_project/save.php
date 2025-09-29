<?php
// 🕒 Set the local timezone to Cairo (Egypt)
date_default_timezone_set("Africa/Cairo");

// Check if the "temp" parameter was received via POST method
if(isset($_POST['temp'])){
    $temp = $_POST['temp'];  // Store the received temperature value
    $img = "";               // Initialize image variable

    // --- Temperature classification ---
    // Select an image based on the temperature range
    if($temp <= 30){
        $img = "cold.png";       // Cold temperature
    } elseif($temp > 30 && $temp < 50){
        $img = "warm.png";       // Moderate temperature
    } else {
        $img = "hot.png";        // High temperature
    }

    // --- Save the data to data.txt file ---
    $file = fopen("data.txt","a");  // Open the file in append mode
    fwrite($file, date("Y-m-d h:i:s A")." - Temp: ".$temp." C - IMG: ".$img."\n");  // Write formatted line
    fclose($file);  // Close the file after writing

    // Display a confirmation message with the temperature and selected image
    echo "Saved: $temp C with $img";
} else {
    // If no temperature was received, show an error message
    echo "No Temperature Received";
}
?>
