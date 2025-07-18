import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;
    import java.util.Base64;
    import javax.imageio.ImageIO;
    import java.awt.image.BufferedImage;
    import java.io.File;
    import java.io.IOException;
    class ImageToData {
        public static void main(String[] args) throws Exception {
            String imageName = "example.png";
            File imageFile = new File(imageName);
            BufferedImage bImage = ImageIO.read(imageFile);
            byte[] imageBytes = null;
            try {
                imageBytes = convertToBytes(bImage, "png");
            } catch (IOException e) {
                System.out.println("Error converting to bytes: "+e);
            }
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydatabase", "username", "password");
            String sql = "INSERT INTO images (id, image) VALUES (?, ?)";
            PreparedStatement pstmt = con.prepareStatement(sql);
            // convert byte data to Base64 string
            String base64ImageString = Base64.getEncoder().encodeToString(imageBytes);
            pstmt.setInt(1, 12345);
            pstmt.setString(2, base64ImageString);
            int row = pstmt.executeUpdate();
            System.out.println("Inserted rows: "+row);
        }
        private static byte[] convertToBytes(BufferedImage image, String format) throws IOException {
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            ImageIO.write(image, format, outputStream);
            return outputStream.toByteArray();
        }
    }