import flask 
from yaml import load, FullLoader
app = Flask(__name__)
@app.route('/')
def home():
    payload = request.args.get('payload')
    if not payload:
        return "Error: No payload parameter found", 400
    try:
        yaml_data = load(payload, Loader=FullLoader)
    except yaml.YAMLError as exc:
        return f"Error: Invalid YAML {exc}", 422
    if yaml_data['type'] != 'Create':
        return "Error: Unsupported operation", 405
    # handle create request here