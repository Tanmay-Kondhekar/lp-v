# Cpp

## General
1. Lib - `<omp.h>`

2. func/direc. - 
    
    `#pragma omp parallel for{}`.

    `#pragma omp parallel for reduction(+:sum){}`

    `omp_get_thread_num()`

    `omp_get_num_threads()`

3. Aggregations -> reduction

    `reduction(+:sum)`
    
    `reduction(*:product)`
    
    `reduction(max:max_val)`
    
    `reduction(min:min_val)`

4. Execution Rule -> `g++ file.cpp -fopenmp -o file && ./file`

## Problem Specifics
1. BFS - 

        current_level = [0]
        Loop:
            next_level = []
            For each node in current_level (PARALLEL):
                explore neighbors
                add new nodes to next_level
            current_level = next_level



# Pys

## Gnerall

1. imp.Imports -> 

        import pandas as pd
        from sklearn.model_selection import train_test_split
        from sklearn.preprocessing import LabelEncoder, StandardScaler
        from tensorflow.keras.models import Sequential
        from tensorflow.keras.layers import Dense
        from tensorflow.keras.layers import Conv2D, MaxPooling, Flatten


        (x_train, y_train), (x_test, y_test) = tf.keras.datasets fashion_mnist.load_data()


## Code spec.
1.  MINIST FASHION

        x_train, x_test = x_train/255, x_test/255

        model = models.Sequential([
            layers.Reshape((28, 28, 1), input_shape=(28, 28)),
            layers.Conv2D(32, 3, activation='relu'),
            layers.MaxPooling2D(),
            layers.Conv2D(64, 3, activation='relu'),
            layers.MaxPooling2D(),
            layers.Flatten(),
            layers.Dense(64, activation='relu'),
            layers.Dense(10, activation='softmax')
        ])

        model.compile(
            optimizer = 'adam',
            loss = 'sparse_categorical_crossentropy',
            metrics = ['accuracy']
        )

2. Letter Recog.

        df = pd.read_csv("letter-recognition/letter-recognition.data")
        x = df.iloc[:, 1:]
        y = df.iloc[:, 0]

        y = LabelEncoder().fit_transform(y)
        x = StandardScaler().fit_transform(x)

        model = ks.models.Sequential([
        ks.layers.Dense(64, activation='relu'),
        ks.layers.Dense(32, activation='relu'),
        ks.layers.Dense(26, activation='softmax')
        ])

        model.compile(
            optimizer='adam',
            loss='sparse_categorical_crossentropy',
            metrics=['accuracy']
        )

3. Boston

        import sklearn.metrics as met

        a = met.root_mean_squared_error(y_test, y_pred)
        b = met.mean_absolute_error(y_test, y_pred)
        c = met.r2_score(y_test, y_pred)

        model  = Sequential([
            Input(shape=(x.shape[1],)),
            Dense(128, activation='relu'),
            Dense(64, activation='relu'),
            Dense(1)
        ])

        model.compile(optimizer='adam', loss='mse')