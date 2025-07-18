@GetMapping(value = "/img")
    public void img() throws IOException {
        String filename = request.args.get("file");
        File file = new File(filename);
        InputStream is = new FileInputStream(file);
        OutputStream os = response.getOutputStream();
        int i;
        while ((i = is.read()) != -1) {
            os.write(i);
        }
    }