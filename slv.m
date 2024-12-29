% Объявление параметров
% Матрица фигуры (например, треугольник)
shape = [
    40, -40, 60;  % Точка 1
    20, -20, 20;  % Точка 2
    60, -20, 20;  % Точка 3
    60, -60, 20;
    20, -60, 20;
];

PROJECTION = [
    0.7, -0.4, 0, 0;
    0, 0.8, 0, 0;
    -0.7, -0.4, 1, 0;
    0, 0, 0, 1
];

% Параметры трансформации
% Смещение
dx = 5; dy = 5; dz = 5;

% Угол вращения (в градусах)
theta_x = pi/6;  % Вокруг оси X
theta_y = pi/6;  % Вокруг оси Y
theta_z = pi/6;  % Вокруг оси Z

% Масштабирование
scale_factor = 0.4;

% Меню для пользователя
disp('Выберите тип преобразования:');
disp('1 - Переместить');
disp('2 - Повернуть');
disp('3 - Увеличить или уменьшить');
disp('4 - Спроецировать');
choice = input('Ваш выбор: ');


% Преобразование фигуры
switch choice
    case 1  % Перемещение
        T_translate = [
            1, 0, 0, dx;
            0, 1, 0, dy;
            0, 0, 1, dz;
            0, 0, 0, 1
        ];
        shape_homogeneous = [shape, ones(size(shape, 1), 1)]'; % Гомогенная матрица
        transformed_shape = (T_translate * shape_homogeneous)';
        transformed_shape = transformed_shape(:, 1:3);  % Убираем гомогенную координату
        
    case 2  % Вращение
        % Преобразование углов в радианы
        theta_x = deg2rad(theta_x);
        theta_y = deg2rad(theta_y);
        theta_z = deg2rad(theta_z);

        % Матрицы вращения
        R_x = [
            1, 0, 0, 0;
            0, cos(theta_x), sin(theta_x), 0;
            0, -sin(theta_x), cos(theta_x), 0;
            0, 0, 0, 1
        ];

        R_y = [
            cos(theta_y), 0, -sin(theta_y), 0;
            0, 1, 0, 0;
            sin(theta_y), 0, cos(theta_y), 0;
            0, 0, 0, 1
        ];

        R_z = [
            cos(theta_z), sin(theta_z), 0, 0;
            -sin(theta_z), cos(theta_z), 0, 0;
            0, 0, 1, 0;
            0, 0, 0, 1
        ];

        % Общая матрица вращения
        R = R_x * R_y * R_z;

        shape_homogeneous = [shape, ones(size(shape, 1), 1)]'; % Гомогенная матрица
        transformed_shape = (R * shape_homogeneous)';
        transformed_shape = transformed_shape(:, 1:3);  % Убираем гомогенную координату
        
    case 3  % Масштабирование
        S = [
            scale_factor, 0, 0, 0;
            0, scale_factor, 0, 0;
            0, 0, scale_factor, 0;
            0, 0, 0, 1
        ];
        shape_homogeneous = [shape, ones(size(shape, 1), 1)]'; % Гомогенная матрица
        transformed_shape = (S * shape_homogeneous)';
        transformed_shape = transformed_shape(:, 1:3);  % Убираем гомогенную координату
    
    case 4
        shape_homogeneous = [shape, ones(size(shape, 1), 1)]'; % Преобразование в гомогенные координаты
        projected_shape = PROJECTION * shape_homogeneous; % Применение проекции
        projected_shape = projected_shape'; % Преобразуем обратно в строки
        projected_shape = projected_shape(:, 1:3); % Убираем гомогенные координаты
        disp('Проецированная фигура:');
        disp(projected_shape);  % Вывод проецированной фигуры
   
    otherwise
        disp('Некорректный выбор.');
        transformed_shape = shape;
end

% Результат
disp('Исходная фигура:');
disp(shape);
disp('Преобразованная фигура:');
disp(transformed_shape);