import java.io.*;
public class UploadImage {
    public static void main(String[] args) throws Exception{
        File inputFile = new File("image.jpg");//This will be the name of the image file that you are uploading
        String base64Image; //The string to hold our Base 64 data
        try {
            byte[] imageBytes = readImage(inputFile);
            base64Image = encodeToString(imageBytes, "png");//Here we assume that the uploaded image is a png file. You can change this accordingly.
            System.out.println("Base 64 string: " + base64Image);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    private static byte[] readImage(File inputFile) throws Exception{
        FileInputStream fis = new FileInputStream(inputFile);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        int data;
        while((data=fis.read())!=-1){
            baos.write(data);
        }
        byte[] imageBytes = baos.toByteArray();
        fis.close();
        return imageBytes;
    }

    private static String encodeToString(byte[] imageBytes, String type) throws Exception{
        String base64Image;
        ByteArrayOutputStream os = new ByteArrayOutputStream();
        try {
            ImageIO.write(imageBytes, type, os);
            byte[] bytes = os.toByteArray();
            base64Image = Base64.getEncoder().encodeToString(bytes);
        } catch (Exception e) {
            System.err.println("Error in encoding the image: " + e.getMessage());
            return null;
        } finally {
            if(os != null){
                os.close();
            }
        }
        return base64Image;
    }
}