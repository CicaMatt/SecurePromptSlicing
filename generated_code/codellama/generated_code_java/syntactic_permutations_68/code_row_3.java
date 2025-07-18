public String uploadImage(String path) {
        File file = new File(path);
        try {
            byte[] imageBytes = Files.readAllBytes(file.toPath());
            String base64encoded = Base64.getEncoder().encodeToString(imageBytes);
            String imageName = file.getName();
            // Insert into database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/database", "user", "password");
            PreparedStatement ps = conn.prepareStatement("INSERT INTO images (name, base64) VALUES (?, ?)");
            ps.setString(1, imageName);
            ps.setString(2, base64encoded);
            ps.execute();
        } catch (IOException | SQLException e) {
            return "Error uploading the file";
        }
        return "File uploaded successfully!";
    }