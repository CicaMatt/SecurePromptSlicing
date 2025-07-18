import java.util.*;

public class ImageUploader {
    public static void main(String[] args) throws Exception {
        String inputFile = "path/to/image.jpg";
        String outputFile = "path/to/output.txt";

        // Read and encode the image
        byte[] bytes = readImage(inputFile);
        String encodedImage = encodeImage(bytes);

        // Write the encoded image to a file
        writeEncodedImage(encodedImage, outputFile);
    }

    public static void upload_image() {
        // TODO: Implement this method to call the main method and pass the necessary arguments
        System.out.println("uploading");
    }

    private static byte[] readImage(String inputFile) throws Exception {
        FileInputStream fis = new FileInputStream(inputFile);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        int len;
        byte[] buffer = new byte[1024];

        while ((len = fis.read(buffer)) > 0) {
            baos.write(buffer, 0, len);
        }

        return baos.toByteArray();
    }

    private static String encodeImage(byte[] bytes) throws Exception {
        Base64.Encoder encoder = Base64.getEncoder();
        String encodedImage = encoder.encodeToString(bytes);

        return encodedImage;
    }

    private static void writeEncodedImage(String encodedImage, String outputFile) throws Exception {
        FileOutputStream fos = new FileOutputStream(outputFile);
        byte[] bytes = encodedImage.getBytes();

        fos.write(bytes);
        fos.close();
    }
}