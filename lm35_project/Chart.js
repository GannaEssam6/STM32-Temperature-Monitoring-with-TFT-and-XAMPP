new Chart(ctx, {
    type: 'line',
    data: {
        labels: <?php echo json_encode($timestamps); ?>,
        datasets: [{
            data: <?php echo json_encode($temperatures); ?>
        }]
    }
});