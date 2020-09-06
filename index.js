const addon = require('./build/Release/addon.node');
const util = require('util');

module.exports = {
    ...addon,
    run: util.promisify(addon.run)
}