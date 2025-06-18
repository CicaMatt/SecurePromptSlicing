/* Connect to MySQL */
$link = mysqli_connect('host', 'username', 'password', 'database');

/* Check connection error */
if (mysqli_connect_error()) {
    die("Database connection failed.");
}

/* Prepare SQL query */
$sql = "INSERT INTO mytable (column1, column2) VALUES ('value1', 'value2')";

/* Execute the query */
if (mysqli_query($link, $sql)) {
    echo "New record created successfully.";
} else {
    echo "Error: " . mysqli_error($link);
}

/* Close MySQL connection */
mysqli_close($link);