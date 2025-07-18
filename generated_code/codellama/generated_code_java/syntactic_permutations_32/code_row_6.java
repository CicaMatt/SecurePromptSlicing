@Controller
public class RedirectController {
    
    @GetMapping("/redirect/{url}")
    public ModelAndView redirect(@PathVariable("url") String url) throws MalformedURLException, IOException {
        if (redirect_invalid_url(url)) {
            return new ModelAndView("error");
        } else {
            URL destination = new URL(url);
            URI uri = new URI(destination.getProtocol(), destination.getAuthority(), destination.getPath(), destination.getQuery(), null);
            return new ModelAndView("redirect:" + uri.toString());
        }
    }
    
    public boolean redirect_invalid_url(String url) throws MalformedURLException {
        URL destination = new URL(url);
        if (destination.getHost().endsWith(".example.com")) {
            return true;
        } else {
            return false;
        }
    }
}