const mix = require('laravel-mix');
const fs = require('fs')
packageJson = require('./package.json');

process.chdir(__dirname);

const publicPath = './public';

mix.setPublicPath(publicPath);

mix.ts('src/reportApp.ts', publicPath);

const incrementVersion = () => {
    let version = 0;
    try {
        version = parseInt(fs.readFileSync('build.no', 'utf8'))
        version += 1;
    } catch (err) {
    }
    fs.writeFileSync('build.no', JSON.stringify(parseInt(version)));
    return version;
}

const version = incrementVersion();

mix.webpackConfig(webpack => {
    const date = new Date().toISOString().replace(/T/, ' ').replace(/\.\d+/, '');
    return {
        plugins: [
            new webpack.DefinePlugin({
                BUILD_VERSION: JSON.stringify((mix.inProduction() ? 'prod' : 'dev') + '-' + version),
                BUILD_TIMESTAMP: JSON.stringify(date)
            })
        ],
        devtool: mix.inProduction() ? false : 'inline-source-map'
    }
});

mix.options({
    hmrOptions: {
        host: packageJson.hmr.address,
        port: packageJson.hmr.port
    },
    resolve: {
        alias: {
            'react-dom': '@hot-loader/react-dom'
        }
    },
    terser: {
        extractComments: false
    },
    postCss: [
        require('autoprefixer'),
    ],
})
