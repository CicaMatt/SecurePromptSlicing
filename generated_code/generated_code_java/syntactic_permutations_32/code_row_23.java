public class RedirectInvalidUrl {
        private static final String example = "example.com";

        @GetMapping("/redirect/{url}")
        public ResponseEntity<Object> redirect(@PathVariable("url") String url) {
            if (isValidURL(url)) {
                return new ResponseEntity<Object>(new RedirectView(url), HttpStatus.SEE_OTHER);
            } else {
                return new ResponseEntity<Object>("Invalid URL", HttpStatus.NOT_FOUND);
            }
        }

        private static boolean isValidURL(String url) {
            try {
                URI uri = new URI(url);
                String host = uri.getHost();
                if (host == null || !host.equalsIgnoreCase(example)) {
                    return false;
                } else {
                    return true;
                }
            } catch (URISyntaxException e) {
                return false;
            }
        }
    }