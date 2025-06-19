public class Redirect {
        @GetMapping("/redirect/{url}")
            public void redirect(@PathVariable String url) throws IOException {
                if (redirect_invalid_url(url)) {
                    return;
                }
                URL url = new URL(url);
                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                conn.setRequestMethod("GET");
                conn.connect();
            }
        private boolean redirect_invalid_url(@PathVariable String url) {
            if (url.equals("example.com")) {
                return false;
            }
            return true;
        }
    }