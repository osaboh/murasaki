/**
 * \file murasaki_defs.hpp
 *
 * \date 2017/11/05
 * \author takemasa
 * \brief common definition of the platfrom.
 */

#ifndef MURASAKI_DEFS_HPP_
#define MURASAKI_DEFS_HPP_

// Following symbols are at the moment of 2018/Apr
#if defined (STM32F756xx) || defined (STM32F746xx) || defined (STM32F745xx) || defined (STM32F767xx) || \
    defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx) || defined (STM32F722xx) || \
	defined (STM32F723xx) || defined (STM32F732xx) || defined (STM32F733xx)
#include "stm32f7xx_hal.h"

#elif defined (STM32F301x8) || defined (STM32F302x8) || defined (STM32F318xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx) || \
    defined (STM32F303x8) || defined (STM32F334x8) || defined (STM32F328xx) || \
    defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F373xC) || defined (STM32F378xx)
#include "stm32f3xx_hal.h"

#elif defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) || \
    defined (STM32L151xB) || defined (STM32L151xBA) || defined (STM32L151xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L151xDX) || defined (STM32L151xE) || \
    defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L152xDX) || defined (STM32L152xE) || \
    defined (STM32L162xC) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L162xDX) || defined (STM32L162xE)
#include "stm32l1xx_hal.h"

#elif defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx) || defined(STM32F070x6) || \
    defined(STM32F070xB) || defined(STM32F030x6)
#include "stm32f0xx_hal.h"
#else
#error "Unknown core"
#endif



#include <FreeRTOS.h>
#include <task.h>

/**
 * \brief Personal Platform parts collection
 * \details
 * This name space encloses personal collections of the software parts to create a "platform" of the software development.
 * This specific collection is based on the STM32Cube HAL and FreeRTOS, both are generated by CubeMX.
 */
namespace murasaki {

/**
 * @ingroup MURASAKI_DEFINITION_GROUP
 * \{
 */

/**
 * @brief Category to filter the Syslog output
 * @details
 * These are independent facilities to filter the Syslog message output.
 * Each module should specify appropriate facility.
 *
 * Internally, these value will be used as bit position in mask.
 */
enum SyslogFacility {
    kfaKernel = 1 << 0,         //!< kfaKernel is specified when the message is bound with the kernel issue.
    kfaSerial = 1 << 1,         //!< kfaSerial is specified when the message is from the serial module.
    kfaSpiMaster = 1 << 2,      //!< kfaSpi is specified when the message is from the SPI master module
    kfaSpiSlave = 1 << 3,       //!< kfaSpi is specified when the message is from the SPI slave module
    kfaI2cMaster = 1 << 4,      //!< kfaI2c is specified when the message is from the I2C master module.
    kfaI2cSlave = 1 << 5,       //!< kfaI2c is specified when the message is from the I2C slave module.
    kfaI2s = 1 << 6,            //!< kfaI2s is specified when the message is from the I2S module
    kfaSai = 1 << 7,            //!< kfaSai is specified when the message is from the SAI module.
    kfaLog = 1 << 8,            //!< kfaLog is specified when the message is from the logger and debugger module.
    kfaNone = 1 << 22,          //!< Disable all facility
    kfaAll = 1 << 23,           //!< Enable all facility
    kfaUser0 = 1 << 24,         //!< User defined facility
    kfaUser1 = 1 << 25,         //!< User defined facility
    kfaUser2 = 1 << 26,         //!< User defined facility
    kfaUser3 = 1 << 27,         //!< User defined facility
    kfaUser4 = 1 << 28,         //!< User defined facility
    kfaUser5 = 1 << 29,         //!< User defined facility
    kfaUser6 = 1 << 30,         //!< User defined facility
    kfaUser7 = 1 << 31          //!< User defined facility
};

/**
 * @brief Message severity level
 * @details
 * The lower value is the more serious condition.
 */
enum SyslogSeverity {
    kseEmergency = 0,    //!< kseEmergency means the system is unusable.
    kseAlert,        //!< kseAlert means some acution must be taken immediately.
    kseCritical,         //!< kseCritical means critical condition.
    kseError,            //!< kseError means error conditions.
    kseWarning,          //!< kseWarning means warning condition.
    kseNotice,           //!< kseNotice means normal but significant condition.
    kseInfomational,     //!< kseInfomational means infomational message.
    kseDebug             //!< kseDebug means debug-level message
};

/**
 * \enum WaitMilliSeconds
 * \brief Wait time by milliseconds. For the function which has "wait" or "timeout" parameter.
 * \details
 * An uint32_t derived type for specifying wait duration. The integer value represents the waiting duration by mili-seconds.
 * Usually a value of this type is passed to some functions as parameter. There are two special cases.
 *
 * kwmsPolling means function will return immediately regardless of waited event.In other word, with this parameter,
 * function causes time out immediately.
 * Some function may provides the way to know what was the status of the waited event. But some may not.
 *
 * kwmsIndefinitely means function will will not cause time out.
 */
enum WaitMilliSeconds
    : uint32_t
    {
        kwmsPolling = 0,               ///< Not waiting. Immediate timeout.
    kwmsIndefinitely = HAL_MAX_DELAY   ///< Wait forever
};

/**
 * \brief Attribute of the UART Hardware Flow Control.
 * \details
 * This is dedicated to the \ref UartStrategy class.
 */
enum UartHardwareFlowControl
{
    kuhfcNone,      ///< No hardware flow control
    kuhfcCts,       ///< Control CTS, but RTS
    kuhfcRts,       ///< Control RTS, but CTS
    kuhfcCtsRts     ///< Control Both CTS and RTS
};
/**
 * \brief SPI clock configuration for Master.
 * \details
 * This enum represents the setting of the SPI POL bit of the master configuration.
 * The POL setting 0/1 is RiseThenFall and Fall thenRise respectively.
 */
enum SpiClockPolarity
{
    kspoRiseThenFall = 0,       //!< kscpRiseThenFall POL = 0
    kspoFallThenRise            //!< kscpFallThenrise POL = 1
};

/**
 * \brief SPI clock configuration for master
 * \details
 * This enum represents the setting of the SPI PHA bit of the master configuration.
 * The PHA setting 0 and 1 is LatchThenShift and ShiftThenLatch respectively.
 */
enum SpiClockPhase
{
    ksphLatchThenShift = 0,     //!< kscpLatchThenShift PHA=0. The first edge is latching. The second edge is shifting.
    ksphShiftThenLatch          //!< kscpShiftThenLatch PHA = 1. The first edge is shifting. The second edge is latching.
};

/**
 * @brief Return status of the I2C classes.
 * @details
 * This enums represents the return status from the I2C class method.
 *
 * In a single master controler system, you need to care only ki2csNak and ki2csTimeOut.
 * Other error may be caused by multiple master system.
 *
 * The ki2csNak is returned when one of two happens :
 * @li The slave device terminated transfer.
 * @li No slave device responded to the address specified by master device.
 *
 * The ki2csTimeOUt is returned when slave device streched transfere too long.
 *
 * The ki2csArbitrationLost is returned when another master won the arbitration. Usulally, the master have to
 * re-try the transfer after certain waiting period.
 *
 * The ki2csBussError is fatal condition. In the master mode, it could be problem of other device.
 * The root cause is not deterministic. Probably it is hardware problem.
 */
enum I2cStatus
{
    ki2csOK = 0,                //!< ki2csOK
    ki2csTimeOut,               //!< Master mode error. No response from device.
    ki2csNak,                   //!< Master mode error. Device answeres NAK
    ki2csBussError,             //!< Master&Slave mode error. START/STOP condition at irregular location.
    ki2csArbitrationLost,       //!< Master&Slave mode error. Lost arbitration against other master device.
    ki2csOverrun,               //!< Slave mode error. Overrun or Underrun was detected.
    ki2csDMA,                   //!< Some error detected in DMA module.
    ki2csSizeError,
    ki2csUnknown                //!< Unknown error
};

/**
 * @brief Return status of the SPI classes
 * @details
 * This enums represents the return status of from the SPI class method.
 *
 * kspisModeFault is returned when the NSS pins are aserted. Note that the Murasaki library doesn't support
 * the Multi master SPI operation. So, this is fatal condition.
 *
 * kpisOverflow and the kpisDMA are fatal condition. These can be the problem of the lower driver problem.
 *
 */
enum SpiStatus
{
    kspisOK = 0,                //!< ki2csOK
    kspisTimeOut,               //!< Master mode error. No response from device.
    kspisModeFault,             //!< SPI mode fault error. Two master corrision
    kspisModeCRC,               //!< CRC protocol error
    kspisOverflow,              //!< Over run.
    kspisFrameError,            //!< Error on TI frame mode.
    kspisDMA,                   //!< DMA error
    kspisErrorFlag,             //!< Other error flag.
    kspisAbort,                 //!< Problem in abort process. No way to recover.
    kspisUnknown                //!< Unknown error
};

/**
 * @brief Return status of the UART classes.
 * @details
 * The Parity error and the Frame error may occur when user connects DCT/DTE by different
 * communicaiton setting.
 *
 * The Noise error may cuase by the noise on the line.
 *
 * The overrun may cause when the DMA is too slow or hand shake is not working well.
 *
 * The DMA error may cause some problem inisde HAL.
 *
 */
enum UartStatus
{
    kursOK = 0,     //!< No error
    kursTimeOut,    //!< Time out during transmission / receive.
    kursParity,     //!< Parity error
    kursNoise,      //!< Error by Noise
    kursFrame,      //!< Frame error
    kursOverrun,    //!< Overrun error
    kursDMA,        //!< Error inside DMA module.
    kursUnknown

};

/**
 * @brief This is specific enum for the AbstractUart::Receive() to specify the use of idle line timeout
 * @details
 * The idle line time out is dedicated function of the STM32 peripherals. The interrrupt happens
 * when the receive data is discontinued certain time.
 */
enum UartTimeout
{
    kutNoIdleTimeout = 0,           //!< kutNoIdleTimeout is specified when API should has normal timeout.
    kutIdleTimeout                  //!< kutIdleTimeout is specified when API should time out by Idle line
};
/**
 * \brief determine task or ISR context
 * \returns true if task context, false if ISR context.
 */
static inline bool IsTaskContext()
{
    // portNVIC_INT_CTRL_REG is mapped to the address 0xe000ed04 by portmacro.h. This register is
    // officially called as NVIC ICSR by ARM
    // This register is common among CORTX-M3, M4 and M7 ( Not checked M0 and M1 )
    // The bit field 8:0 displays the on-going ISR number. So, if this field is 0, it is task context.
    // ( Note : This is just guess. ARM technical manual is not cleear when this field is 0 ).
    // This register and field is suggested to use to detect the context in this page.
    // https://www.freertos.org/FreeRTOS_Support_Forum_Archive/September_2014/freertos_How_to_determine_current_context_type_-_interrupt_or_task_87aef448j.html
    // But the answer in this page seems to be wrong. It is referring only LSB 5bits. For the specific
    // LPC4330 which is focused in this page, 0x1F is still too short.
    // To extract the entire bit field 8:0, the bit mask have to be 0x1FF

    return ((portNVIC_INT_CTRL_REG & 0x1FF) == 0);

}

/**
 * @brief Clean and Flush the specific region of data cache.
 * @param address Start address of region
 * @param size Size of region
 * @details
 * Keep coherence between the L2 memory and d-cache, between specific region.
 *
 * The region is specified by address and size. If address si not 32byte aligned,
 * it is truncated to the 32byte alignment, and size is adjusted to follow this alignment.
 *
 * Once this function is returned, the specific region is coherent.
 */
static inline void InvalidateDataCacheByAddress(void * address, size_t size)
{
#ifdef __CORE_CM7_H_GENERIC
    unsigned int aligned_address = reinterpret_cast<unsigned int>(address);

    // extract modulo 32. The address have to be aligned to 32byte.
    unsigned int adjustment = aligned_address & 0x1F;
    // Adjust the address and size.
    aligned_address -= adjustment;  // aligne to 32byte boarder
    size += adjustment;             // Because the start address is lower, the size is bigger.

    ::SCB_InvalidateDCache_by_Addr(reinterpret_cast<long unsigned int *>(aligned_address), size);
#elif defined ( __CORE_CM0_H_GENERIC ) ||defined ( __CORE_CM0PLUS_H_GENERIC ) ||defined ( __CORE_CM3_H_GENERIC ) ||defined ( __CORE_CM4_H_GENERIC )
    // Do nothing. These core doesn't have d-cache.
#else
#error "Unknown core"
#endif
}

/**
 *
 * @brief Keep task sleeping during the specific duration.
 * @param duration Sleeping time by milliseconds.
 * @details
 * Whenever this function is called, that task gets into the sleeping ( or waiting, the name is up to RTOS ) immediately.
 * Then, wake up after specified duration.
 *
 * Note that the duration is interpreted as "at least". The actual sleeping duration could be longer than
 * the specified duration by parameter. The worst error between the actual duration and the specified duration is
 * the period of the tick in system.
 *
 * For example, if the tick period is 10mS, the worst error is 10mS.
 */
static inline void Sleep(murasaki::WaitMilliSeconds duration) {
    vTaskDelay(pdMS_TO_TICKS(duration));
}
/**
 * \}
 * end of ingroup MURASAKI_DEFINITION_GROUP Definitions
 *
 */




}     // namespace


#endif /* MURASAKI_DEFS_HPP_ */
