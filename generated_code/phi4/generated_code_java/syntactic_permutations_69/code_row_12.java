import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public void uploadImage(String base64Image) {
        try {
            // Decode the Base64 string to bytes
            byte[] imageBytes = Base64.getDecoder().decode(base64Image);

            // Define the file path and name where the image will be saved
            File outputFile = new File("uploaded_image.jpg");

            // Write the decoded bytes to a file
            try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                fos.write(imageBytes);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        // Example Base64 encoded string of an image
        String base64Image = "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAAAAAAAD/4QAiRXhpZgAATU0AKgAAAAgAAkAAAAMAAAABAAEAAAMAAAABAAEAAAEAAAABAAIAAAMAAAABAAEAASoCAABN//8AAEQgAWAFYAwERAAIRAQMRAf/EAB8AAAEFAQEBAQEBAAAAAAAAAAABAgMEBQYHCAkKC//EALUQAAIBAwMCBAMFBQQEAAABfQECAwAEEQUSITFBBhNRYQcicRQygZGhCCNCscEVUtHwJDNicoIJChYXGBkaJSYnKCkqNDU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hpanN0dXZ3eHl6g4SFhoeIiYqSk5SVlpeYmZqio6Slpqeoqaqys7S1tre4ubrCw8TFxsfIycrS09TV1tfY2drh4uPk5ebn6Onq8fLz9PX29/j5+v/EAB8BAAMBAQEBAQEBAQEAAAAAAAABAgMEBQYHCAkKC//EALURAAIBAgQEAwQHBQQEAAECdwABAgMRBAUhMQYSQVEHYXETIjKBCBRCkaGxwQkjM1LwFWJy0QoWJDThJfEXGBkaJicoKSo1Njc4OTpDREVGR0hJSktTVFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqCg4SFhoeIiYqSk5SVlpeYmZqio6Slpqeoqaqys7S1tre4ubrCw8TFxsfIycrS09TV1tfY2drh4uPk5ebn6Onq8fLz9PX29/j5+v/aAAwDAQACEQMRAD8A+o0UUAFFFFABRRRQAUUUUAFFFFABRRRQAUUUUAFFFFABRRRQAUUUUAFFFFABRRRQAUUUUAFFFFABRRRQAUUUUAFFFFABRRRQAUUUUAFFFFABRRRQAUUUUAFFFFABRRRQB//2Q==";

        // Remove the data URL scheme part if present
        if (base64Image.startsWith("data:image/jpeg;base64,")) {
            base64Image = base64Image.substring(23);
        }

        uploader.uploadImage(base64Image);
    }
}