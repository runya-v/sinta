var list = {
	"Информация": {
		"Проект": [
            ["Описание", "description"],
            ["Контакты", "contacts"]
		]
	},

	"Программирование": {
		"Основы": [
			[ "Страуструп", "panorama" ],
			[ "Стандарт C++ 11", "panorama" ],
			[ "Старый добрый STL", "panorama" ],
			[ "Частые вопросы по CMake", "panorama" ],
			[ "Параллельное программирование на С++", "programming/multithreading" ]
		],

		"Любимый Boost": [
			[ "ASIO", "programming/boost-asio" ],
			[ "Юнит тесты", "programming/boost-test" ]
		],

		"Алгоритмы": [
			[ "Фундаментальные алгоритмы", "panorama" ],
			[ "Сборник алгоритмов", "panorama" ],
			[ "Шень", "panorama" ],
			[ "Кнут 1", "panorama" ],
			[ "Кнут 2", "panorama" ],
			[ "Кнут 3", "panorama" ],
			[ "Приёмы программирования", "panorama" ],
			[ "Алгоритмические задачи", "panorama" ]
		],

		"Графика": [
			[ "OpenGL", "panorama" ],
			[ "Программирование компьютерной графики", "panorama" ]
		],

		"AI": [
			[ "Искусственный интеллект в играх", "panorama" ]
		],

		"Астрономия": [
			[ "Астрономия", "panorama" ],
		],

		"Проекты": [
			[ "Слот автоматы", "panorama" ],
			[ "Уголки", "panorama" ],
			[ "Сетевой движок, Rise of flight", "panorama" ],
			[ "Сетевой движок, социальные игры", "panorama" ],
			[ "Render", "panorama" ],
			[ "Sphinks", "panorama" ],
			[ "Парсер вёрсток", "panorama" ],
			[ "Python разные полезности", "projects/python" ],
			[ "Flash 3D панорама", "projects/flash" ]
		]
	},
    
    "Электроника" : {
		"Исследование полей": [
			[ "Карта сна", "panorama" ],
			[ "Осциллограф", "panorama" ]
		],

		"Робототехника": [
			[ "Сигвей", "panorama" ]
		]
    }
};

var pages = {};

for ( var section in list ) {
	pages[ section ] = {};

	for ( var category in list[ section ] ) {
		pages[ section ][ category ] = {};

		for ( var i = 0; i < list[ section ][ category ].length; i ++ ) {
			var page = list[ section ][ category ][ i ];
			pages[ section ][ category ][ page[ 0 ] ] = page[ 1 ];
		}
	}
}
