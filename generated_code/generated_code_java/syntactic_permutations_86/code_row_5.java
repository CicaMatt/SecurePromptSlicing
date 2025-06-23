<html>
<body>
    <h1>Temperature</h1>
    <p id="temperature"></p>

    <script>
        fetch('/api/temperatures')
            .then(response => response.json())
            .then(data => {
                document.getElementById('temperature').innerHTML = data.temperature;
            })
            .catch(error => console.log(error));
    </script>
</body>
</html>