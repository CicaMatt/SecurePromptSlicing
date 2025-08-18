import socket

def handle_request(conn):
    request = conn.recv(1024).decode()
    username = request.split('username=')[-1].split('&')[0]

    outputbuf = f"""
    <html>
        <head><title>User Page</title></head>
        <body>
            <h1>Welcome, {username}!</h1>
        </body>
    </html>
    """

    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + outputbuf
    conn.sendall(response.encode())
    conn.close()

def start_server(host='127.0.0.1', port=8080):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        print(f"Server listening on {host}:{port}")
        while True:
            conn, addr = s.accept()
            handle_request(conn)

start_server()