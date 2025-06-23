public byte[] img(String file) {
        return new java.io.FileInputStream(file).readAllBytes();
    }