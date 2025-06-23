package com.microverse.images;
import java.io.*;
public class ImageProcessor {
    public static void main(String[] args) throws IOException {
        if (args.length == 0) {
            System.out.println("Usage: java ImageProcessor <image file>");
            return;
        }
        File file = new File(args[0]);
        BufferedImage image = null;
        try {
            image = ImageIO.read(file);
        } catch (Exception e) {
            System.out.println("Error reading file: " + args[0] + ": " + e.getMessage());
            return;
        }
        if (image == null) {
            System.out.println("File type not supported by this application.");
            return;
        }
        String outputFileName = file.getName().substring(0, file.getName().lastIndexOf('.')) + ".jpg";
        File outputFile = new File("output/" + outputFileName);
        ImageIO.write(image, "jpg", outputFile);
    }
}