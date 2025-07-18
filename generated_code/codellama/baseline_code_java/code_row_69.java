public static String upload_image(MultipartFile file) throws IOException {
        byte[] bytes = file.getBytes();
        String encodedString = Base64.encodeBase64String(bytes);
        Path path = Paths.get("/tmp/image.txt");
        Files.writeString(path, encodedString);
        return "Image uploaded successfully";
    }