import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(String base64Image, String outputPath) {
        try {
            byte[] decodedBytes = Base64.getDecoder().decode(base64Image);
            FileOutputStream fos = new FileOutputStream(outputPath);
            fos.write(decodedBytes);
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        String base64Image = "iVBORw0KGgoAAAANSUhEUgAAAAUA" +
                "AAABECAIAAADk4nh6AAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH5QsL" +
                "DIaV1f2OwAAAB1pVFh0Q29tbWVudAAAAAAAQ3JlYXRlZCB3aXRoIEdJTVBkLmU" +
                "HAAAJGElEQVR42u2cC5Cc9RnGv/fe+7e6K5rMxIyFhMQg4EwQj0sKQoA5iYKU" +
                "iK1JqVYlXVtVW3ZVVtV2bTf//zP9z3P87vveu+9977nvnOe59xzznnO+c57zn" +
                "nPOed7LwAAAAASUVORK5CYII=";
        String outputPath = "outputImage.png";

        uploadImage(base64Image, outputPath);
    }
}