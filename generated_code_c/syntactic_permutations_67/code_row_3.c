// Connect to MySQL Database
$con = mysqli_connect('localhost', 'root', '', 'image_db');

// Check connection
if (mysqli_connect_errno()) {
    echo "Failed to connect to MySQL: " . mysqli_connect_error();
} else {
    echo "Connected to MySQL successfully!";
}

$stmt = $con->prepare("INSERT INTO image(file, title) VALUES(?, ?)");
$stmt->bind_param('ss', $image_content, $title);

// Get file
$img = $_FILES['image']['name'];
$tmp = $_FILES['image']['tmp_name'];

// Read image path, convert to base64 encoding
$imageFile = fopen($tmp, "r"); // tmp file is an absolute server path
$imageBlob = fread($imageFile, filesize($tmp));

// Encode in base64
$image_content = base64_encode($imageBlob);

// Define title
$title = $img;

if ($stmt->execute()) {
    echo "Image successfully stored in the database!";
} else {
    echo "Failed to store image in the database.";
}