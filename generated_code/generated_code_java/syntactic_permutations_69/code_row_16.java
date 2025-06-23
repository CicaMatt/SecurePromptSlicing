package com.mycompany;
    
    import org.apache.commons.codec.binary.Base64;
    import java.io.*;
    import javax.servlet.http.*;
    
    public class ImageUpload {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            //get the image from the input form control
            Part filePart = request.getPart("uploadedImage");
            InputStream imageInputStream = null;
            if (filePart != null) {
                try {
                    //read the contents of the uploaded image
                    imageInputStream = filePart.getInputStream();
                } catch (IOException e) {
                    System.out.println("Error reading uploaded image.");
                }
            } else {
                System.out.println("No image was specified");
            }
    
            //encode the image using base64
            byte[] bytes = new byte[imageInputStream.available()];
            imageInputStream.read(bytes);
            String encodedImage = Base64.encodeBase64String(bytes);
    
            //write the encoded image to a text file
            FileWriter writer = new FileWriter("encodedImage.txt");
            writer.write(encodedImage);
            writer.close();
        }
    }