<!DOCTYPE html>
<html lang="ar">
<head>
    <meta charset="UTF-8">
    <title>لوحة مراقبة الحرارة</title>

    <!-- Auto-refresh the page every 30 seconds to update data -->
    <meta http-equiv="refresh" content="30">

    <!-- Load Chart.js library for drawing temperature chart -->
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

    <!-- Basic styling for the dashboard -->
    <style>
        body { font-family: Arial; background-color: #f4f4f4; padding: 30px; }
        h1, h2 { text-align: center; color: #333; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th, td { border: 1px solid #ccc; padding: 10px; text-align: center; }
        img { width: 80px; }
        .refresh-btn { display: block; margin: 20px auto; padding: 10px 20px; font-size: 16px; }
        canvas { display: block; margin: 40px auto; }
    </style>
</head>
<body>

<!-- Dashboard Title -->
<h1>📊 لوحة مراقبة الحرارة</h1>

<!-- Manual refresh button (GET method) -->
<form method="get">
    <button class="refresh-btn">🔄 تحديث البيانات</button>
</form>

<?php
// Define the data file path
$dataFile = "data.txt";

// Read lines from the file if it exists
$lines = file_exists($dataFile) ? file($dataFile) : [];

// Arrays to store timestamps and temperature values for the chart
$timestamps = [];
$temperatures = [];

if (!empty($lines)) {
    // Display the latest reading
    $latest = end($lines);
    echo "<h2>🕒 آخر قراءة:</h2>";
    echo "<p style='font-size:18px; text-align:center;'>$latest</p>";

    // Display all readings in a table
    echo "<h2>📋 كل القراءات:</h2>";
    echo "<table><tr><th>الوقت</th><th>الحرارة</th><th>الصورة</th></tr>";

    // Loop through each line and extract data
    foreach ($lines as $line) {
        // Extract timestamp from the beginning of the line
        $time = strtok($line, " -");

        // Extract temperature using regular expression
        preg_match("/Temp: ([\d.]+) C/", $line, $matches);
        $temp = $matches[1] ?? "N/A";

        // Extract image filename after "IMG:"
        $img = trim(explode("IMG:", $line)[1] ?? "");

        // Display the data in a table row
        echo "<tr><td>$time</td><td>$temp °C</td><td><img src='$img'></td></tr>";

        // Store data for the chart
        $timestamps[] = $time;
        $temperatures[] = floatval($temp);
    }

    echo "</table>";
} else {
    // If no data is available, show a warning message
    echo "<p style='color:red; text-align:center;'>لا توجد بيانات حتى الآن.</p>";
}
?>

<!-- Temperature Chart Section -->
<h2>📉 رسم بياني للحرارة:</h2>
<canvas id="tempChart" width="800" height="400"></canvas>

<script>
    // Initialize the chart using Chart.js
    const ctx = document.getElementById('tempChart').getContext('2d');
    const tempChart = new Chart(ctx, {
        type: 'line', // Line chart
        data: {
            labels: <?php echo json_encode($timestamps); ?>, // X-axis labels (timestamps)
            datasets: [{
                label: 'درجة الحرارة (°C)', // Chart label
                data: <?php echo json_encode($temperatures); ?>, // Y-axis data (temperatures)
                backgroundColor: 'rgba(54, 162, 235, 0.2)', // Fill color
                borderColor: 'rgba(54, 162, 235, 1)',       // Line color
                borderWidth: 2,
                fill: true,
                tension: 0.3 // Curve smoothness
            }]
        },
        options: {
            scales: {
                x: { title: { display: true, text: 'الوقت' } }, // X-axis title
                y: { title: { display: true, text: 'درجة الحرارة (°C)' }, beginAtZero: true } // Y-axis title
            }
        }
    });
</script>

</body>
</html>