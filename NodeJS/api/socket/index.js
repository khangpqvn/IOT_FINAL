var express = require('express');
var router = express.Router();
var controller = require('./controler');

/**
 * @swagger
 * /socket/push:
 *   post:
 *     tags:
 *       - Socket
 *     description: Send code to device via socket
 *     produces:
 *       - application/json
 *     parameters:
 *       - name: info about device
 *         description: info about device want to get
 *         in: body
 *         required: true
 *         schema:
 *           type: object
 *           example: {"key_event": "send","push_data":"Code send here","mac_address":"Mac of device you need to send code"}
 *     responses:
 *       200:
 *         description: thành công.
 *       400:
 *         description: Bad request.
 *       403:
 *         description: Schedule is existed.
 *       500:
 *         description: Lỗi chưa được xác định
 *       503:
 *         description: Dịch vụ không sẵn dùng
 */
router.post("/push", controller.pushNotice);


/**
 * @swagger
 * /socket/listMacOnline:
 *   get:
 *     tags:
 *       - Socket
 *     description: Send code to device via socket
 *     produces:
 *       - application/json
 *     responses:
 *       200:
 *         description: thành công.
 *       400:
 *         description: Bad request.
 *       403:
 *         description: Schedule is existed.
 *       500:
 *         description: Lỗi chưa được xác định
 *       503:
 *         description: Dịch vụ không sẵn dùng
 */
router.get("/listMacOnline", controller.getConnectedDevides);

/**
 * @swagger
 * /socket/listDevices:
 *   get:
 *     tags:
 *       - Socket
 *     description: Send code to device via socket
 *     produces:
 *       - application/json
 *     responses:
 *       200:
 *         description: thành công.
 *       400:
 *         description: Bad request.
 *       403:
 *         description: Schedule is existed.
 *       500:
 *         description: Lỗi chưa được xác định
 *       503:
 *         description: Dịch vụ không sẵn dùng
 */
router.get("/listDevices", controller.listDevices);

module.exports = router;