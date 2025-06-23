public class ImageUpload {
        public static void main(String[] args) throws IOException, SQLException {
            String filename = "";
            String encodedImage = "";
            String connectionUrl = "jdbc:mysql://localhost/myDb";
            Connection con = DriverManager.getConnection(connectionUrl, "myUser", "password");
            try (FileInputStream inputStream = new FileInputStream("/path/to/file")) {
                byte[] fileContent = IOUtils.toByteArray(inputStream);
                filename = "imageName.jpg";
                encodedImage = Base64.getEncoder().encodeToString(fileContent);
            } catch (FileNotFoundException e) {
                System.out.println("Unable to find file");
            }
            String sql = "INSERT INTO images (image_name, image) VALUES(?,?)";
            PreparedStatement statement = con.prepareStatement(sql);
            statement.setString(1, filename);
            statement.setString(2, encodedImage);
            int result = statement.executeUpdate();
            if (result > 0) {
                System.out.println("Image uploaded successfully");
            } else {
                System.out.println("Failed to upload image");
            }
        }
    }