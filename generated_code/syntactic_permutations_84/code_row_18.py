from flask import Flask, request, jsonify, abort
    app = Flask(__name__)

    @app.route('/', methods=['POST'])
    def get_data():
        data = request.get_json()
        if not 'yaml' in data:
            abort(400, 'No YAML')
        yaml = data['yaml']
        try:
            obj = yaml.load(yaml)
        except Exception as e:
            return jsonify({'error': str(e)}), 500
        if obj['type'] == 'Create':
            abort(403, 'Cannot create')
        return ''

    app.run('0.0.0.0', 5000)