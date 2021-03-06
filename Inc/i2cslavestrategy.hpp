/**
 * @file i2cslavestrategy.hpp
 *
 * @date 2018/10/07
 * @author takemasa
 *  \brief Root class definition of the I2C Slave.
 */

#ifndef I2CSLAVESTRATEGY_HPP_
#define I2CSLAVESTRATEGY_HPP_

#include <peripheralstrategy.hpp>

namespace murasaki {
/**
 * \ingroup MURASAKI_ABSTRACT_GROUP
 * \brief Definition of the root class of I2C Slave.
 * \details
 * A prototype of the I2C slave peripheral.
 *
 * This prototype assumes the derived class will transmit / receive data in the
 * task context on RTOS. And these member functions should be blocking.
 * That mean, until the transmit / receive terminates, both method doesn't return.
 *
 * Two call back member functions are prepared to sync with the interrupt which tells the end of
 * Transmit/Receive.
 */
class I2cSlaveStrategy : public murasaki::PeripheralStrategy {
 public:
    /**
     * @brief Thread safe, blocking transmission over I2C.
     * @param tx_data Data array to transmit.
     * @param tx_size Data counts[bytes] to transmit.
     * @param transfered_count the count of the bytes transfered during the API execution.
     * @param timeout_ms Time ou [mS]. By default, there is not timeout.
     * @return Result of the processing
     * @details
     * This member function is programmed to run in the task context of RTOS. This should be internally
     * exclusive between multiple task access. In other word, it should be thread save.
     */
    virtual murasaki::I2cStatus Transmit(
                                         const uint8_t * tx_data,
                                         unsigned int tx_size,
                                         uint * transfered_count = nullptr,
                                         murasaki::WaitMilliSeconds timeout_ms = murasaki::kwmsIndefinitely) = 0;
    /**
     * @brief Thread safe, blocking receiving over I2C.
     * @param rx_data Data array to transmit.
     * @param rx_size Data counts[bytes] to transmit.
     * @param transfered_count the count of the bytes transfered during the API execution.
     * @param timeout_ms Time ou [mS]. By default, there is not timeout.
     * @return Result of the processing
     * @details
     * This member function is programmed to run in the task context of RTOS. This should be internally
     * exclusive between multiple task access. In other word, it should be thread save.
     */
    virtual murasaki::I2cStatus Receive(
                                        uint8_t * rx_data,
                                        unsigned int rx_size,
                                        uint * transfered_count = nullptr,
                                        murasaki::WaitMilliSeconds timeout_ms = murasaki::kwmsIndefinitely) = 0;

    /**
     * \brief Call back to be called notify the transfer is complete.
     * \param ptr Pointer for generic use. Usually, points a struct of a peripheral control
     * \return true: ptr matches with peripheral and handle the call back. false : doesn't match.
     * \details
     * A call back to notify the end of entire block or byte transfer. The definition of calling timing is
     * depend on the implementation. This is called from an DMA ISR.
     *
     *
     * Typically, an implementation may check whether the given ptr parameter matches its own device, and if matched, handle it
     * and return true. If it doesn't match, just return false.
     */
    virtual bool TransmitCompleteCallback(void* ptr)=0;
    /**
     * \brief Call back to be called for entire block transfer is complete.
     * \param ptr Pointer for generic use. Usually, points a struct of a peripheral control
     * \return true: ptr matches with peripheral and handle the call back. false : doesn't match.
     * \details
     * A call back to notify the end of entire block or byte transfer. The definition of calling timing is
     * depend on the implementation. This is called from an DMA ISR.
     *
     * Typically, an implementation may check whether the given ptr parameter matches its own device, and if matched, handle it
     * and return true. If it doesn't match, just return false.
     */
    virtual bool ReceiveCompleteCallback(void* ptr) = 0;
    /**
     * @brief Handling error report of device.
     * @param ptr Pointer for generic use. Usually, points a struct of a device control
     * @return true if ptr matches with device and handle the error. false if ptr doesn't match
     * A member function to detect error.
     *
     * The error handling is depend on the implementation.
     */
    virtual bool HandleError(void * ptr)= 0;
};

}  // namespace

#endif /* I2CSLAVESTRATEGY_HPP_ */
