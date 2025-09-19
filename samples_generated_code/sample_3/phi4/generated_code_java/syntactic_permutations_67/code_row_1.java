import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide an image file path as a command line argument.");
            return;
        }

        String filePath = args[0];
        File imageFile = new File(filePath);

        if (!imageFile.exists()) {
            System.out.println("The specified file does not exist.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", "username", "password")) {

            byte[] imageData = readFileToByteArray(imageFile);
            
            String sql = "INSERT INTO images_table (image_data) VALUES (?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setBlob(1, new java.sql.Blob() {
                    @Override
                    public byte[] getBinaryVal(long pos, int len) throws SQLException {
                        return imageData;
                    }

                    @Override
                    public InputStream getBinaryStream(long pos, int length) throws SQLException {
                        return new ByteArrayInputStream(imageData);
                    }

                    @Override
                    public long length() throws SQLException {
                        return (long) imageData.length;
                    }

                    @Override
                    public String characterSet() throws SQLException {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public void free() throws SQLException {
                        // No resources to free
                    }
                });

                statement.executeUpdate();
                System.out.println("Image successfully stored in the database.");
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] readFileToByteArray(File file) throws Exception {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            fis.read(data);
            return data;
        }
    }
}


**Note:** Replace `"your_database_name"`, `"username"`, and `"password"` with your actual database name, username, and password. Also, ensure that `images_table` and its column `image_data` exist in your database schema.