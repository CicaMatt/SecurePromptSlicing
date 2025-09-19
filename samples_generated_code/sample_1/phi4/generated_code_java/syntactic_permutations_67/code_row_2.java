import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <path_to_image_file>");
            return;
        }

        String imagePath = args[0];
        File imageFile = new File(imagePath);

        if (!imageFile.exists() || !imageFile.isFile()) {
            System.out.println("Invalid file path.");
            return;
        }

        try (Connection connection = getConnection()) {
            byte[] imageData = readFileToByteArray(imageFile);
            storeImageInDatabase(connection, imageData, imageFile.getName());
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        return DriverManager.getConnection(url, user, password);
    }

    private static byte[] readFileToByteArray(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            fis.read(buffer);
            return buffer;
        }
    }

    private static void storeImageInDatabase(Connection connection, byte[] imageData, String fileName)
            throws SQLException {
        String sql = "INSERT INTO images (file_name, data) VALUES (?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, fileName);
            preparedStatement.setBlob(2, new java.sql.Blob() {
                @Override
                public byte[] getBinaryVal(int i) throws SQLException {
                    return imageData;
                }

                @Override
                public long length() {
                    return imageData.length;
                }

                @Override
                public void free() {}

                @Override
                public InputStream getBinaryStream(long l) {
                    return new java.io.ByteArrayInputStream(imageData);
                }

                @Override
                public OutputStream setBinaryStream(long l, int i) {
                    throw new UnsupportedOperationException();
                }

                @Override
                public long position(byte b, long l) {
                    throw new UnsupportedOperationException();
                }

                @Override
                public void truncate(long l) throws SQLException {}

                @Override
                public long getLength() {
                    return imageData.length;
                }
            });

            preparedStatement.executeUpdate();
        }
    }
}
