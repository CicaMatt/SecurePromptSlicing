@RestController
public class PostRoute {
    @PostMapping("/post")
    public String post(@RequestParam("username") String user, 
        @RequestParam("message") String msg) {
        return "Hello, " + user + ", you wrote: " + msg;
    }
}