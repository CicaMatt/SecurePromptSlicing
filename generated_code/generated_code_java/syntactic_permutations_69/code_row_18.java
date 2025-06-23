import java.io.File;
    import java.util.Base64;

    public class ImageUtil {

        private static File uploadImage(String filePath) {
            try {
                String base64Encoded = encodeToBase64(filePath);
                writeToFile(base64Encoded, "encoded_image.txt");
            } catch (Exception e) {
                System.out.println("Error in uploading image: " + e.getMessage());
            }
        }

        private static String encodeToBase64(String filePath) throws Exception {
            File file = new File(filePath);
            byte[] fileContent = new byte[(int) file.length()];
            new FileInputStream(file).read(fileContent);
            return Base64.getEncoder().encodeToString(fileContent);
        }

        private static void writeToFile(String content, String fileName) {
            try (FileWriter writer = new FileWriter(fileName)) {
                writer.write(content);
            } catch (Exception e) {
                System.out.println("Error in writing to file: " + e.getMessage());
            }
        }
    }