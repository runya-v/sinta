var SINTA = {VERSIION: '0.1'};


SINTA.Scene = function(num_birds) {
    var _camera;
    var _scene;
    var _renderer;
    var _birds = [];
    var _boids = [];
    var _texture_placeholder;
    var _is_user_interacting = false;
    var _on_mouse_down_mouse_x = 0;
    var _on_mouse_down_mouse_y= 0;
    var _on_mouse_down_lon = 0;
    var _on_mouse_down_lat = 0;
    var _lon = 90;
    var _lat = 0;
    var _pi = 0;
    var _theta = 0;
    var _target = new THREE.Vector3();

    function render() {
        _lat = Math.max(-85, Math.min(85, _lat));
        _pi = THREE.Math.degToRad(90 - _lat);
        _theta = THREE.Math.degToRad(_lon);
        _target.x = 500 * Math.sin(_pi) * Math.cos(_theta);
        _target.y = 500 * Math.cos(_pi);
        _target.z = 500 * Math.sin(_pi) * Math.sin(_theta);
        _camera.lookAt(_target);
        _renderer.render(_scene, _camera);
    }

    function onWindowResize() {
        _camera.aspect = window.innerWidth / window.innerHeight;
        _camera.updateProjectionMatrix();
        _renderer.setSize(window.innerWidth, window.innerHeight);
        render();
    }

    function onDocumentMouseDown(e) {
        e.preventDefault();
        _is_user_interacting = true;
        _on_mouse_down_mouse_x = e.clientX;
        _on_mouse_down_mouse_y = e.clientY;
        _on_mouse_down_lon = _lon;
        _on_mouse_down_lat = _lat;
    }

    function updateBirdsMov(e) {
        var v = new THREE.Vector3(e.clientX - (window.innerWidth / 2), -e.clientY + (window.innerHeight / 2), 0);
        for (var i = 0, il = _boids.length; i < il; i++) {
            var boid = _boids[i];
            v.z = boid.position.z;
            boid.repulse(v);
        }
    }

    function onDocumentMouseMove(e) {
        if (_is_user_interacting) {
            _lon = (_on_mouse_down_mouse_x - e.clientX) * 0.1 + _on_mouse_down_lon;
            _lat = (e.clientY - _on_mouse_down_mouse_y) * 0.1 + _on_mouse_down_lat;
            render();
        }
        updateBirdsMov(e);
    }

    function onDocumentMouseUp(e) {
        _is_user_interacting = false;
        render();
    }

    function onDocumentMouseWheel(e) {
        _camera.fov -= e.wheelDeltaY * 0.05;
        _camera.updateProjectionMatrix();
        render();
    }

    function onDocumentTouchStart(e) {
        if (e.touches.length == 1) {
            e.preventDefault();
            _on_mouse_down_mouse_x = e.touches[0].pageX;
            _on_mouse_down_mouse_y = e.touches[0].pageY;
            _on_mouse_down_lon = _lon;
            _on_mouse_down_lat = _lat;
        }
    }

    function onDocumentTouchMove(e) {
        if (e.touches.length == 1) {
            e.preventDefault();
            _lon = (_on_mouse_down_mouse_x - e.touches[0].pageX) * 0.1 + _on_mouse_down_lon;
            _lat = (e.touches[0].pageY - _on_mouse_down_mouse_y) * 0.1 + _on_mouse_down_lat;
            render();
        }
    }

    function renderBirds() {
        for (var i = 0, il = _birds.length; i < il; i++) {
            var boid = _boids[i];
            boid.run(_boids);
            var bird = _birds[i];
            var color = bird.material.color;
            color.r = (500 - bird.position.z) / 1000;
            color.g = color.r;
            color.b = color.r;
            bird.rotation.y = Math.atan2(-boid.velocity.z, boid.velocity.x);
            bird.rotation.z = Math.asin(boid.velocity.y / boid.velocity.length());
            bird.phase = (bird.phase + (Math.max(0, bird.rotation.z) + 0.1)) % 62.83;
            bird.geometry.vertices[5].y = bird.geometry.vertices[4].y = Math.sin(bird.phase) * 5;
        }
        _renderer.render(_scene, _camera);
    }

    function loadTexture(path) {
        var texture = new THREE.Texture(_texture_placeholder);
        var material = new THREE.MeshBasicMaterial({ map:texture, overdraw:true });
        var image = new Image();
        image.onload = function() {
            texture.needsUpdate = true;
            material.map.image = this;
            render();
        };
        image.src = path;
        return material;
    }

    this.init = function() {
        var scene_style = document.createElement('style');
        scene_style.innerHTML = "#scene_container{width:100%; height:100%; touch-action:none;}";
        document.head.appendChild(scene_style);

        var scene_container = document.createElement('div');
        scene_container.id = "scene_container";
        document.body.appendChild(scene_container);

        _camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 1, 1100);
        _renderer = new THREE.CanvasRenderer();
        _renderer.setSize(window.innerWidth, window.innerHeight);
        scene_container.appendChild(_renderer.domElement);

        _texture_placeholder = document.createElement('canvas');
        _texture_placeholder.width = 128;
        _texture_placeholder.height = 128;
        var ct = _texture_placeholder.getContext('2d');
        ct.fillStyle = 'rgb( 200, 200, 255 )';
        ct.fillRect(0, 0, _texture_placeholder.width, _texture_placeholder.height);

        var materials = [
            loadTexture('images/skybox/px.jpg'), // right
            loadTexture('images/skybox/nx.jpg'), // left
            loadTexture('images/skybox/py.jpg'), // top
            loadTexture('images/skybox/ny.jpg'), // bottom
            loadTexture('images/skybox/pz.jpg'), // back
            loadTexture('images/skybox/nz.jpg')  // front
        ];
        var mesh = new THREE.Mesh(
            new THREE.CubeGeometry(1000, 1000, 1000, 10, 10, 10),
            new THREE.MeshFaceMaterial(materials));
        mesh.scale.x = -1;
        _scene = new THREE.Scene();
        _scene.add(mesh);

        for(var i = 0; i < num_birds; i++) {
            var boid = new Boid();
            _boids[i] = boid;
            boid.position.x = Math.random() * 400 - 200;
            boid.position.y = Math.random() * 400 - 200;
            boid.position.z = Math.random() * 400 - 200;
            boid.velocity.x = Math.random() * 2 - 1;
            boid.velocity.y = Math.random() * 2 - 1;
            boid.velocity.z = Math.random() * 2 - 1;
            boid.setAvoidWalls(true);
            boid.setWorldSize(500, 500, 400);
            var bird = new THREE.Mesh(
                new Bird(),
                new THREE.MeshBasicMaterial({ color:Math.random() * 0xffffff, side: THREE.DoubleSide }));
            bird.position = _boids[i].position;
            bird.phase = Math.floor(Math.random() * 62.83);
            _birds[i] = bird;
            _scene.add(bird);
        }

        document.addEventListener('mousedown',  onDocumentMouseDown,  false);
        document.addEventListener('mousemove',  onDocumentMouseMove,  false);
        document.addEventListener('mouseup',    onDocumentMouseUp,    false);
        document.addEventListener('mousewheel', onDocumentMouseWheel, false);
        document.addEventListener('touchstart', onDocumentTouchStart, false);
        document.addEventListener('touchmove',  onDocumentTouchMove,  false);
        window.addEventListener('resize', onWindowResize, false);
    };

    this.animate = function() {
        var sinta = this;
        requestAnimationFrame(sinta.animate.bind(sinta));
        _lon += 0.01;
        _lat = Math.max(-85, Math.min(85, _lat));
        _pi = THREE.Math.degToRad(90 - _lat);
        _theta = THREE.Math.degToRad(_lon);
        _target.x = Math.sin(_pi) * Math.cos(_theta);
        _target.y = Math.cos(_pi);
        _target.z = Math.sin(_pi) * Math.sin(_theta);
        _camera.lookAt(_target);
        renderBirds();
        _renderer.render(_scene, _camera);
    };
};


function main() {
    var scene = new SINTA.Scene(100);
    scene.init();
    scene.animate();
    var ui = new UI.View();
    new ui.Container(10, 10, window.innerWidth - 20, window.innerHeight - 20);
};


main();